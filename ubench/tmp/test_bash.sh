#!/bin/bash

#XYZ="blah"

if [ -z ${XYZ} ]; then
	XYZ="blah2"
	echo ${XYZ}
else
	echo ${XYZ}
fi
