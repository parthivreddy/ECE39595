import sys

ifp = open("simple_poly.txt")
ifp2 = open("result.txt")

temp = ifp.readline()
temp2 = ifp2.readline()
ofp1 = open("poly1.txt", "w")
ofp2 = open("poly2.txt", "w")
ofp3 = open("polyResult.txt", "w")

while(temp2[0] != ";"):
    power = 0
    coeff = 0
    count = 0
    tempchar = temp2[count]
    coeffvec = []
    powervec = []
    while(tempchar != 'x'):
        coeffvec.append(tempchar)
        count+=1
        tempchar = temp2[count]
    
    count+=2
    tempchar = temp2[count]
    while(tempchar != '\n'):
        powervec.append(tempchar)
        count+=1
        tempchar = temp2[count]
    #print("".join(powervec))
    
    power = ("".join(powervec))
    coeff = ("".join(coeffvec))
    print(", {" + power + "," + coeff + "}", end = "", file = ofp3)
    temp2 = ifp2.readline()

while(temp[0] != ";"):
    power = 0
    coeff = 0
    count = 0
    tempchar = temp[count]
    coeffvec = []
    powervec = []
    while(tempchar != 'x'):
        coeffvec.append(tempchar)
        count+=1
        tempchar = temp[count]
    
    count+=2
    tempchar = temp[count]
    while(tempchar != '\n'):
        powervec.append(tempchar)
        count+=1
        tempchar = temp[count]
    #print("".join(powervec))
    
    power = ("".join(powervec))
    coeff = ("".join(coeffvec))
    print(", {" + power + "," + coeff + "}", end = "", file = ofp1)
    temp = ifp.readline()

temp = ifp.readline()

while(temp[0] != ";"):
    power = 0
    coeff = 0
    count = 0
    tempchar = temp[count]
    coeffvec = []
    powervec = []
    while(tempchar != 'x'):
        coeffvec.append(tempchar)
        count+=1
        tempchar = temp[count]
    
    count+=2
    tempchar = temp[count]
    while(tempchar != '\n'):
        powervec.append(tempchar)
        count+=1
        tempchar = temp[count]
    #print("".join(powervec))
    
    power = ("".join(powervec))
    coeff = ("".join(coeffvec))
    print(", {" + power + "," + coeff + "}", end = "", file = ofp2)
    temp = ifp.readline()
    
