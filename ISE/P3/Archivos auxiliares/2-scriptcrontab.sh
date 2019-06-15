#!/bin/bash

fecha=$(date +"%m_%d_%Y")
mkdir -p ~/seguridad
mkdir -p ~/seguridad/$fecha
cp -r ~/codigo ~/seguridad/$fecha
