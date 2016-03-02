#!/bin/bash

if [ ! -d "core/obj" ]; then 
	mkdir core/obj
fi

if [ ! -d "client/obj" ]; then 
	mkdir client/obj
fi

if [ ! -d "server/obj" ]; then 
	mkdir server/obj
fi

if [ ! -d "centralServer/obj" ]; then 
	mkdir centralServer/obj
fi

if [ ! -f "core/.depend" ]; then
	touch core/.depend
fi

if [ ! -f "client/.depend" ]; then
	touch client/.depend
fi

if [ ! -f "server/.depend" ]; then
	touch server/.depend
fi

if [ ! -f "centralServer/.depend" ]; then
	touch centralServer/.depend
fi