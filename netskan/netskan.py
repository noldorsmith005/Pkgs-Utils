import os
import subprocess
from pythonping import ping



# Get Basic Info

def get_dns():
    line = subprocess.getoutput("ipconfig getsummary en0 | grep domain_name_server")
    newline = line.split(" ")
    dns_addr = newline[2]
    return dns_addr

def get_ip():
    line = subprocess.getoutput("ifconfig en0 | grep mask")
    newline = line.split(" ")
    ip_addr = newline[1]
    broadcast = newline[5]
    return ip_addr, broadcast

def get_subnet():
    line = subprocess.getoutput("ipconfig getsummary en0 | grep subnet_mask")
    newline = line.split(" ")
    mask = newline[2]
    return mask

def get_gateway():
    line = subprocess.getoutput("ipconfig getsummary en0 | grep router")
    newline = line.split(" ")
    gate = newline[2]
    return gate


# Subnet Calculations

def unwrap_subnet():
    print("Unwrapping subnet mask...")

    bit_counter = 0
    oct_ref = [128, 64, 32, 16, 8, 4, 2, 1,]
    mask = get_subnet().split(".")
    increment = 0
    ip_addr = (get_ip()[0])
    net_addr = ""

    for octet in mask:
        octet = int(octet)

        if octet == 255:
            bit_counter += 8
        else :
            octet = [*bin(octet)][2:]

            if len(octet) == 8:
                counter = 0
                for bit in octet:
                    if bit == "1":
                        bit_counter += 1
                        counter += 1
                
                increment = oct_ref[(counter - 1)]

    print(f"/{bit_counter}")
    print(increment)
                
    
        
                





    
    








unwrap_subnet()







