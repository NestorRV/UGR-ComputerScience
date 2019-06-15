#!/bin/bash

echo "SHELL=/bin/sh" >> crontab-reducelista
echo "PATH=`pwd`/:$HOME/SO:"$PATH >> crontab-reducelista
echo "1 * * * * ./reducelista" >> crontab-reducelista
