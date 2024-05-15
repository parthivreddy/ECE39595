import sys

color_dict = {"b":"Black", "w":"White"}
type_dict = {"b":"Bishop", "p":"Pawn", "r":"Rook", "k":"King"}


FILEIN = open(sys.argv[1])
FILEIN.readline()
temp = FILEIN.readline()

n = temp[0]
print("    Student::ChessBoard sBoard(" + n +","+ n + ");")
print()
temp = FILEIN.readline()
while(temp[0] != "~"):
    color = temp[0]
    type_chess =  temp[2]
    row = temp[4]
    col = temp[6]
    print("    sBoard.createChessPiece(" + color_dict[color] +","+ type_dict[type_chess]+ "," + row +","+ col + ");")
    temp = FILEIN.readline()
temp = FILEIN.readline()
while(temp):
    if(temp == "isValidScan\n"):
        print("    sBoard.isValidScan(" + n +","+ n + ");")
    elif(temp == "underThreatScan\n"):
        print("    sBoard.underThreatScan(" + n +","+ n + ");")
        print()
    else:
        fromRow = temp[10]
        fromCol = temp[12]
        toRow = temp[14]
        toCol = temp[16]
        print("    sBoard.movePiece(" + fromRow +","+ fromCol+ "," + toRow +","+ toCol + ");")

    temp = FILEIN.readline()
