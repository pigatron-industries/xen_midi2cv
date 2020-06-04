#!/bin/bash
protoc --plugin=/usr/local/Cellar/nanopb-generator/0.3.9.4/bin/protoc-gen-nanopb --nanopb_out=. ConfigMessage.proto
