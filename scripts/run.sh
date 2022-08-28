#!/bin/bash

if [ "$1" = "release" ]
then
	./bin/release/civilization_autonama
else
	./bin/debug/civilization_autonama
fi