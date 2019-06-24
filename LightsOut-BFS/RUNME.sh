#!/bin/bash

echo Running Lights Out...
javac -d ./src ./src/*.java
java -cp ./src/ Main
