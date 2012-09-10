#!/usr/bin/python

import serial
import sys

import beerduino_pb2

def main(argv):
  if len(argv) < 2:
    print 'Usage: server.py /dev/serial'
    return

  ard_serial = serial.Serial(argv[1], 9600)
  print ard_serial.readline()

  ping_msg = beerduino_pb2.Ping()
  ping_msg.id = 123

  data = ping_msg.SerializeToString()
  ard_serial.write('' + chr(len(data)))
  print 'Writing %d bytes to serial.' % len(data)
  ard_serial.write(data)

  echo_msg = beerduino_pb2.Echo()
  msg_len = ard_serial.read(size=1)
  print 'Reading %d bytes from serial.' % ord(msg_len)
  echo_msg.ParseFromString(ard_serial.read(ord(msg_len)))

  str = 'Received Echo with id: %d.' % echo_msg.id
  if echo_msg.HasField('message'):
    print str + ' Message: %s' % echo_msg.message


if __name__ == '__main__':
  main(sys.argv)
