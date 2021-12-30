


outString = "" # store output as string before printing. Uses more memory but faster

for row in range(5,15,1):
    
    for col in range(0,14,1):
        value =  pow(col - 5, 2) * (-.2) + row  # math equation to make a surface
        outString += str( abs(int(value*1000)) ) # scale it so uint16_t is relevant
        outString += ' '

    outString += '\n'


fileName = "outputSurface.txt"
fout = open(fileName, 'w') # open the file in overwrite mode

print(outString, file=fout) # print to file

print('wrote to file: ', fileName)

fout.close()
