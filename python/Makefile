
.PHONY = clean

NANOPB_DIR = ../nanopb/generator
PROTO_DIR = ../proto
GOOGLE_PROTOBUF_INCLUDES = /usr/local/include
PROTO_INCLUDES = -I$(GOOGLE_PROTOBUF_INCLUDES) -I$(PROTO_DIR) -I$(NANOPB_DIR)

all: beerduino_pb2.py

beerduino_pb2.py: $(PROTO_DIR)/beerduino.proto nanopb_pb2.py
	protoc --python_out=.  $(PROTO_INCLUDES) $<

nanopb_pb2.py: $(NANOPB_DIR)/nanopb.proto
	protoc --python_out=. $(PROTO_INCLUDES) $<

clean:
	rm -rf nanopb_pb2.* beerduino_pb2.*
