// Incluir este codigo en belkan.cpp

// ------- Devuleve en fila y en columna, la fila y la columna que hay en el mensaje que devuelve el entorno.
void CapturaFilaColumnaPK (string mensaje, int &fila, int &columna){
	if (mensaje.substr(0,8)=="PK fila:"){
		int pos = mensaje.find('c');
		string valor = mensaje.substr(9,pos-8);
		fila = atoi(valor.c_str());
		
		int pos2 = mensaje.find('.');
		pos = pos+8;
		valor = mensaje.substr(pos,pos2-1);
		columna = atoi(valor.c_str());
	}
}


// Uso de la función anterior
// int fil, col
// CapturaFilaColumnaPK (MENSAJE_,fil,col);
 
