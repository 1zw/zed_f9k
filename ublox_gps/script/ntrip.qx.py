#!/usr/bin/python3

import socket
import base64
import os
import serial
import yaml

qx_file_path = os.path.abspath(__file__)
script_directory = os.path.dirname(qx_file_path)
config_path = os.path.join(script_directory, "../config/qx.yaml")
with open(config_path, 'r') as stream:
    try:
        config = yaml.safe_load(stream)
    except yaml.YAMLError as exc:
        print(exc)

# load params from qx.yaml
dummyNMEA = config['dummyNMEA']
username = config['username']
password = config['password']
port = config['port']
ip = config['ip']
mountpoint = config['mountpoint']
mountpoint1 = config['mountpoint1']

auth = base64.b64encode("{}:{}".format(username, password).encode('ascii'))
auth = auth.decode('ascii')

portx = config['portx']
bps = config['bps']
timex = config['timex']

ser=serial.Serial(portx,bps,timeout=timex)

print("Header sending... \n")

#Build Header
header =\
"GET /" + mountpoint + " HTTP/1.1\r\n" +\
"Host ip:port\r\n" +\
"Ntrip-Version: Ntrip/1.0\r\n" +\
"User-Agent: ntrip.py/0.2\r\n" +\
"Accept: */*" +\
"Connection: close\r\n" +\
"Authorization: Basic {}\r\n\r\n".format(auth)

header1 =\
"GET /" + mountpoint1 + " HTTP/1.1\r\n" +\
"Host ip:port\r\n" +\
"Ntrip-Version: Ntrip/1.0\r\n" +\
"User-Agent: ntrip.py/0.2\r\n" +\
"Accept: */*" +\
"Connection: close\r\n" +\
"Authorization: Basic {}\r\n".format(auth) 

#Start Connection + send Header
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((ip,int(port)))
s.send(header.encode('ascii'))

print("Waiting for answer...\n")
data = s.recv(2048).decode('ascii')
print(data)
#"Ntrip-GGA: {}".format(dummyNMEA)
#Send NMEA String
print("Sending NMEA String\n")
while True:
  print("Sending NMEA String\n")
  dummyHeader =  \
	"{}\r\n".format(dummyNMEA)
  s.send(dummyHeader.encode('ascii'))

  print("Waiting for answer...\n")

  #rtcm = s.recv(2048).decode('utf-8')
  ser.write(s.recv(2048))
  

ser.close()
s.close()
