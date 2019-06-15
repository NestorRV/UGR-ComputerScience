#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
//gestion de costmaps
#include "tf/transform_listener.h"


#include <boost/thread.hpp>

#include "frontier_explorer_lite.h"

#include <limits>
#include <iostream>
#include <fstream>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

//imprime en pantalla el contendio de un mapa

void printMapa(std::vector< std::vector<int> > mapa) {
    //lo escribe en la orientación correcta, primero escribe las filas superiores ....
    for (int x = 0; x < mapa[0].size(); x++)
        for (int y = mapa.size() - 1; y >= 0; y--) {
            std::cout << (int) mapa[y][x] << " ";
        }
}

void FrontierExplorer::printMapToFile() {
    //Escribe el mapa en el fichero "grid.txt"
    std::ofstream gridFile;
    gridFile.open("grid.txt");

    for (int x = 0; x < theGlobalCm[0].size(); x++) {
        for (int y = theGlobalCm.size() - 1; y >= 0; y--) {
            gridFile << (int) theGlobalCm[y][x] << " ";
        }
        gridFile << std::endl;
    }
    gridFile.close();
}

FrontierExplorer::FrontierExplorer() {
    //Inicializa el explorador de fronteras.
    mapIsEmpty = true;
    posGoal.x = posGoal.y = 0; //Posición del objetivo
    nodoPosicionRobot.x = nodoPosicionRobot.y = 0; //Posición actual
    yaw = 0; //Angulo (en radianes) de orientación del robot
    v_angular = v_lineal = 0.0; //velocidad angular
    // Advertise a new publisher for the simulated robot's velocity command topic
    commandPub = node.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    //Publicador del objetivo en rviz.
    marker_pubobjetivo = node.advertise<visualization_msgs::Marker>("visualizacion_objetivo", 1);
    //Publicador de los nodos de frontera para visuoalizarlos en rviz
    marker_pub = node.advertise<visualization_msgs::Marker>("visualization_marker", 1000);
    //Se subscribe a la posición publicada por la odometría
    odomSub = node.subscribe("odom", 100, &FrontierExplorer::odomCallBack, this);
    //Se subscribe al mapa publicado por gmapping
    mapSub = node.subscribe("map", 100, &FrontierExplorer::getmapCallBack, this);
}

void FrontierExplorer::gira360() {
    ROS_INFO("INFO: Voy a girar 720 grados.");
    ros::Rate rate(10);
    geometry_msgs::Twist msg;
    msg.linear.x = 0;
    commandPub.publish(msg);

    msg.angular.z = 45 * 2 * 3.1415926535897 / 360;
    ros::Time start2 = ros::Time::now();
    while (ros::Time::now() - start2 <= ros::Duration(16.0)) {
        commandPub.publish(msg);
        ros::spinOnce();
        rate.sleep();
    }
    ROS_INFO("INFO: Ya he terminado de girar.");
}

void FrontierExplorer::getmapCallBack(const nav_msgs::OccupancyGrid::ConstPtr& msg) {
    //callback para obtener el mapa.
    int ini_x = 0, fin_x = 0, ini_y = 0, fin_y = 0;
    mapIsEmpty = true; //asumimos que el mapa está vacío antes de recibirlo
    cmGlobal = *msg; //guardamos en la variable cmGlobal el mensaje recibido para
    // disponer del mensaje en nuestro programa
    //redimensiona el  mapa segun las dimensiones del mapa recibido
    theGlobalCm.resize(cmGlobal.info.height); //resize al numero de filas
    for (int y = 0; y < cmGlobal.info.height; y++)
        theGlobalCm[y].resize(cmGlobal.info.width);

    //copia el mapa del mensaje en el mapa del explorador de fronteras
    //informa en mapEmpty si hay celdas con información.
    int currCell = 0;
    for (int y = 0; y < cmGlobal.info.height; y++){
        for (int x = 0; x < cmGlobal.info.width; x++) {
            theGlobalCm[y][x] = cmGlobal.data[currCell];
            if (theGlobalCm[y][x] != -1) mapIsEmpty = false;
            currCell++;
        }
    }

    currCell = 0;
    for (int y = 0; y < cmGlobal.info.height; y++){
        ini_y = y - 10, fin_y = y + 10;
        if(ini_y < 0)
            ini_y = 0;
        if(fin_y > theGlobalCm.size() - 1)
            fin_y = theGlobalCm.size();
        for (int x = 0; x < cmGlobal.info.width; x++) {
            ini_x = x - 10, fin_x = x + 10;
            if(ini_x < 0)
                ini_x = 0;
            if(fin_x > theGlobalCm[0].size() - 1)
                fin_x = theGlobalCm[0].size();
            if (cmGlobal.data[currCell] == 100){
                for(int i = ini_y; i < fin_y; i++){
                    for(int j = ini_x; j < fin_x; j++){
                        rellenaObstaculos(i, j);
                    }
                }
            }
            currCell++;
        }
    }

    //cmGlobal.header.seq = msg->header.seq;
    //cmGlobal.header.stamp = msg->header.stamp;
    //cmGlobal.header.frame_id = msg->header.frame_id;
    //
    //cmGlobal.info.map_load_time = msg->info.map_load_time ;
    //cmGlobal.info.resolution = msg->info.resolution;
    //cmGlobal.info.width = msg->info.width;
    //cmGlobal.info.height = msg->info.height;
    //
    //cmGlobal.info.origin.position.x = msg->info.origin.position.x;
    //cmGlobal.info.origin.position.y = msg->info.origin.position.y;
    //cmGlobal.info.origin.position.z = msg->info.origin.position.z;
    //
    //cmGlobal.info.origin.orientation.x = msg->info.origin.orientation.x;
    //cmGlobal.info.origin.orientation.y = msg->info.origin.orientation.y;
    //cmGlobal.info.origin.orientation.z = msg->info.origin.orientation.z;
    //cmGlobal.info.origin.orientation.w = msg->info.origin.orientation.w;
    //
}

void FrontierExplorer::rellenaObstaculos(int cell_x, int cell_y) {
    theGlobalCm[cell_x][cell_y] = 100;
    if(cell_x > 0){
        theGlobalCm[cell_x - 1][cell_y] = 100;
        if(cell_y > 0)
            theGlobalCm[cell_x - 1][cell_y - 1] = 100;
        if(cell_y < theGlobalCm[0].size() - 1)
            theGlobalCm[cell_x - 1][cell_y + 1] = 100;
    }
    if(cell_x < theGlobalCm.size() - 1){
        theGlobalCm[cell_x + 1][cell_y] = 100;
        if(cell_y > 0)
            theGlobalCm[cell_x + 1][cell_y - 1] = 100;
        if(cell_y < theGlobalCm[0].size() - 1)
            theGlobalCm[cell_x + 1][cell_y + 1] = 100;
    }
    if(cell_y > 0)
        theGlobalCm[cell_x][cell_y - 1] = 100;
    if(cell_y < theGlobalCm[0].size() - 1)
        theGlobalCm[cell_x][cell_y + 1] = 100;
}

void FrontierExplorer::odomCallBack(const nav_msgs::Odometry::ConstPtr& msg) {
    //obtengo la posición. y la guardo en el dato miembro del objeto FrontierExplorer
    nodoPosicionRobot.x = msg->pose.pose.position.x;
    nodoPosicionRobot.y = msg->pose.pose.position.y;
    //también la guardo en FrontierExplorer::odometria
    odometria.pose.pose.position.x = nodoPosicionRobot.x;
    odometria.pose.pose.position.y = nodoPosicionRobot.y;
    //get Quaternion anglular information
    double x = msg->pose.pose.orientation.x;
    double y = msg->pose.pose.orientation.y;
    double z = msg->pose.pose.orientation.z;
    double w = msg->pose.pose.orientation.w;
    //la guardo en la odometría
    odometria.pose.pose.orientation.x = x;
    odometria.pose.pose.orientation.y = y;
    odometria.pose.pose.orientation.z = z;
    odometria.pose.pose.orientation.w = w;

    //convertir to pitch,roll, yaw
    //consultado en http://answers.ros.org/question/50113/transform-quaternion/
    //guardo el yaw en FrontierExplorer::yaw
    yaw = atan2(2 * (y * x + w * z), w * w + x * x - y * y - z * z);
};

bool FrontierExplorer::someNeighbourIsUnknown(int cell_x, int cell_y) {
    //cell_x representa la abcisa de una celda dada del mapa.
    //cell_y representa la ordenada.
    //Devuelve true si hay alguna casilla vecina a la celda dada que es desconocida
    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
            if ((cell_x + x >= 0) && (cell_x + x < cmGlobal.info.width) &&
                    (cell_y + y >= 0) && (cell_y + y < cmGlobal.info.height))
                if (theGlobalCm[cell_y + y][cell_x + x] == -1)
                    return true;
    return false;
}

bool FrontierExplorer::someNeighbourIsObstacle(int cell_x, int cell_y) {
    //cell_x representa la abcisa de una celda dada del mapa.
    //cell_y representa la ordenada.
    //Devuelve true si hay alguna casilla vecina a la celda dada que es un obstáculo
    return true;
}


//calculo de la distancia (sobrecargada) entre dos nodos de frontera o entre dos reales (más abajo)

double distancia(nodeOfFrontier &n1, nodeOfFrontier &n2) {
    return sqrt((pow(n1.x - n2.x, 2)) + pow(n1.y - n2.y, 2));
}

double distancia(double c1_x, double c1_y, double c2_x, double c2_y) {
    return sqrt((pow(c1_x - c2_x, 2)) + pow(c1_y - c2_y, 2));
}

void FrontierExplorer::eraseFrontier(double px, double py) {
    //borra nodos de la frontera a una distancia de dos metros de la posición (px,py)
    TipoFrontera::iterator it = frontera.begin();
    while (it != frontera.end()) {
        if (distancia(px, py, it->x, it->y) <= 2)
            frontera.erase(it);
        else it++;
    }
}

void FrontierExplorer::labelFrontierNodes() {
    //La frontera es un vector de pares de coordenadas (de tipo TipoFrontera)
    //Insertar en frontera los puntos, en coordenadas del mundo, que tienen algún vecino desconocido.
    nodeOfFrontier n;
    frontera.resize(0);
    for(int i = 0; i < theGlobalCm.size(); i++){
        for(int j = 0; j < theGlobalCm[i].size(); j++){
            if(someNeighbourIsUnknown(j, i) && theGlobalCm[i][j] == 0){
                //Debo incluirlo en la frontera
                n.x = (double) j * cmGlobal.info.resolution + cmGlobal.info.origin.position.x;
                n.y = (double) i * cmGlobal.info.resolution + cmGlobal.info.origin.position.y;
                frontera.push_back(n);
            }
        }
    }
}

void FrontierExplorer::selectNode(nodeOfFrontier &selectednode, bool lejos) {
    // Devuelva en el argumento selectedNode un nodo de la frontera seleccionado siguiendo 
    // algún criterio (distancia mínima a la posición actual del robot, o distancia máxima, o 
    // aquél que tenga la mayor zona desconocida en su entorno cercano, ...).
    int indice = 0;
    double d_actual = 0, d;
    if(lejos){
        d = -1;
        for(int i = 0; i < frontera.size(); i++){
            d_actual = distancia(nodoPosicionRobot, frontera[i]);
            if(d_actual > d && d_actual > 0.15){
                d = d_actual;
                indice = i;
            }
        }
    } else{
        d = 999999;
        for(int i = 0; i < frontera.size(); i++){
            d_actual = distancia(nodoPosicionRobot, frontera[i]);
            if(d_actual < d && d_actual > 0.15){
                d = d_actual;
                indice = i;
            }
        }
    }
    ROS_INFO("TASK: Elegido: %i. x: %f. y: %f. dist: %f.", indice, frontera[indice].x, frontera[indice].y, d);
    selectednode = frontera[indice];
}

/********VISUALIZAR FRONTERA *************************/

void FrontierExplorer::inicializaMarkerSphere(std::string ns, int id, float r, float g, float b) {
    marker_objetivo.header.frame_id = "map";
    marker_objetivo.header.stamp = ros::Time::now();
    marker_objetivo.ns = ns;

    marker_objetivo.action = visualization_msgs::Marker::ADD; //la otra es DELETE
    marker_objetivo.pose.orientation.w = 0.0;

    marker_objetivo.id = id;

    marker_objetivo.type = visualization_msgs::Marker::SPHERE;

    // POINTS markers use x and y scale for width/height respectively
    marker_objetivo.scale.x = 0.2; //cmGlobal.info.resolution;
    marker_objetivo.scale.y = 0.2; //cmGlobal.info.resolution;

    // Points are green
    marker_objetivo.color.g = g;
    marker_objetivo.color.r = r;
    marker_objetivo.color.b = b;
    marker_objetivo.color.a = 1.0;
}

void FrontierExplorer::inicializaMarkers(std::string ns, int id, float r, float g, float b) {
    markers_frontera.header.frame_id = "map"; //cmGlobal.header.frame_id.c_str();//getGlobalFrameID().c_str();
    markers_frontera.header.stamp = ros::Time::now();
    markers_frontera.ns = ns;

    markers_frontera.action = visualization_msgs::Marker::ADD; //la otra es DELETE
    markers_frontera.pose.orientation.w = 0.0;

    markers_frontera.id = id;

    markers_frontera.type = visualization_msgs::Marker::POINTS;

    // POINTS markers use x and y scale for width/height respectively
    markers_frontera.scale.x = 0.05; //cmGlobal.info.resolution;
    markers_frontera.scale.y = 0.05; //cmGlobal.info.resolution;

    // Points are green
    markers_frontera.color.g = g;
    markers_frontera.color.r = r;
    markers_frontera.color.b = b;
    markers_frontera.color.a = 1.0;
}

void FrontierExplorer::visualizaObjetivo(double x, double y) {
    //PINTO: cpstart.x, cpstart.y, scale == costmap_->getResolution
    limpiaMarkerObjetivo();
    marker_objetivo.pose.position.x = x;
    marker_objetivo.pose.position.y = y;

    marker_pubobjetivo.publish(marker_objetivo); //lo publico
    //points.points.pop_back(); //quito el punto de la lista de puntos, lo borro con DELETE cuando lo saque de abiertos.
}

void FrontierExplorer::visualizaLista(TipoFrontera lista) {
    limpiaMarkers();
    markers_frontera.points.erase(markers_frontera.points.begin(), markers_frontera.points.end());
    for (TipoFrontera::iterator it = lista.begin(); it != lista.end(); ++it) {

        double wpose_x = it->x;
        double wpose_y = it->y;
        //PINTO: cpstart.x, cpstart.y, scale == costmap_->getResolution
        geometry_msgs::Point p;
        p.x = wpose_x;
        p.y = wpose_y;
        p.z = 0; //¿?

        markers_frontera.points.push_back(p);
    }
    marker_pub.publish(markers_frontera);
    //quitar neighborCells de points .popback
}

void FrontierExplorer::limpiaMarkerObjetivo() {
    marker_objetivo.action = visualization_msgs::Marker::DELETE;
    marker_pubobjetivo.publish(marker_objetivo);
    marker_objetivo.action = visualization_msgs::Marker::ADD;
}

void FrontierExplorer::limpiaMarkers() {
    if (!markers_frontera.points.empty()) {
        markers_frontera.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(markers_frontera);
        markers_frontera.action = visualization_msgs::Marker::ADD;
    }
    markers_frontera.points.clear();
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "frontier_explorer_node");

    ROS_INFO("El timeout a usar es: %f", strtod(argv[1], NULL));

    // create the action client	
    MoveBaseClient ac("move_base", true);
    // Wait 60 seconds for the action server to become available
    ROS_INFO("INFO: Waiting for the move_base action server");
    ac.waitForServer(ros::Duration(60));
    ROS_INFO("INFO: Connected to move base server");

    //inicializa el explorador
    FrontierExplorer explorador;
    //inicializa la visualización de la frontera
    explorador.inicializaMarkers("frontera", 0, 0.0f, 1.0f, 0.0f);
    //inicializa la visualización del objetivo seleccionado.
    explorador.inicializaMarkerSphere("objetivo", 0, 0.0, 0.0, 1.0);
    //hacemos que se gestionen las callbacks hasta que el mapa tenga información
    ROS_INFO("INFO: Esperando a que mapa reinicie y tenga información");
    while (explorador.mapIsEmpty)
        ros::spinOnce();
    //ROS_INFO("YA SE QUE EL MAPA NO ESTÁ VACÍO %d filas, %d columnas", explorador.cmGlobal.info.height, explorador.cmGlobal.info.width);
    ros::Rate frecuencia(0.2);
    nodeOfFrontier nodo, antiguo;
    bool alcanzado = false;
    int elegido;
    move_base_msgs::MoveBaseGoal goal;

    while (ros::ok()) {
        explorador.gira360();
        explorador.labelFrontierNodes();
        explorador.visualizaLista(explorador.frontera);
        
        explorador.selectNode(nodo, true);
        antiguo.x = explorador.nodoPosicionRobot.x;
        antiguo.y = explorador.nodoPosicionRobot.y;
        explorador.visualizaObjetivo(nodo.x, nodo.y);
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();	
        goal.target_pose.pose.position.x = nodo.x;
        goal.target_pose.pose.position.y = nodo.y;
        goal.target_pose.pose.orientation.w = 1;

        ac.sendGoal(goal);
        ac.waitForResult(ros::Duration(strtod(argv[1], NULL)));

        if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
            ROS_INFO("TASK: You have reached the goal!");
            alcanzado = true;
        }
        else{
            ROS_INFO("TASK: The base failed for some reason");
            alcanzado = false;
        }

        //printMapa(explorador.theGlobalCm);
        ROS_INFO("INFO: Escribiendo mapa en fichero de texto.");
        explorador.printMapToFile();
        ROS_INFO("INFO: Posicion actual del robot (%f %f %f)", explorador.nodoPosicionRobot.x, explorador.nodoPosicionRobot.y, explorador.yaw);

        ROS_INFO("INFO: Esperando a finalizar el bucle");
        frecuencia.sleep();
        ros::spinOnce();

        int contador = 0;
        if(!alcanzado){
            ROS_INFO("TASK: No se ha alcanzado el objetivo. Intento: %i", contador);
            do{
                explorador.visualizaObjetivo(antiguo.x, antiguo.y);
                goal.target_pose.header.frame_id = "map";
                goal.target_pose.header.stamp = ros::Time::now();	
                goal.target_pose.pose.position.x = antiguo.x;
                goal.target_pose.pose.position.y = antiguo.y;
                goal.target_pose.pose.orientation.w = 1;

                ac.sendGoal(goal);
                ac.waitForResult(ros::Duration(strtod(argv[1], NULL) / 2));

                if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
                    ROS_INFO("TASK: You have reached the goal!");
                    alcanzado = true;
                }
                else{
                    ROS_INFO("TASK: The base failed for some reason");
                    alcanzado = false;
                    contador++;
                }

                //printMapa(explorador.theGlobalCm);
                ROS_INFO("INFO: Escribiendo mapa en fichero de texto.");
                explorador.printMapToFile();
                ROS_INFO("INFO: Posicion actual del robot (%f %f %f)", explorador.nodoPosicionRobot.x, explorador.nodoPosicionRobot.y, explorador.yaw);

                ROS_INFO("INFO: Esperando a finalizar el bucle");
                frecuencia.sleep();
                ros::spinOnce();
                if(!alcanzado){
                    explorador.selectNode(nodo, false);
                    ROS_INFO("TASK: No se he podido volver, voy al primero nodo. Intento: %i", contador);
                }
                if(contador == 3)
                    alcanzado = true;
            }while(!alcanzado);
        }
    }

    // shutdown the node and join the thread back before exiting
    ros::shutdown();

    return 0;
}
