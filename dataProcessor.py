names = ["maxValue", "mean", "correctedMean", "nbZeros"]

maxlength = 0;

for filename in names:
    
    MyFile = open("./"+filename+".csv", "r");
    
    rawFile = MyFile.read();
    rawLines = rawFile.split("\n");
    MyFile.close();
    
    

    # Load da table :
    table=[]
    for line in rawLines:
        table.append(line.split(","));
        maxlength = max( len(line.split(",")) , maxlength);
        
        
    MyFile = open("./CleanDatas/"+filename+".csv", "a");
    MyFile.write(filename+",")
    
    for i in range(maxlength-1):
        somme = 0;
        totNbValues = 0;
        
        for j in range(len(rawLines)-1):
            if (i < len(table[j])-1):
                somme += float(table[j][i]);
                totNbValues += 1;
        
        MyFile.write( str(float(somme)/float(totNbValues)) + ",")
        
    MyFile.close()
                
                       
            
MyFile = open("./CleanDatas/n.csv", "a");
MyFile.write("n,")
for i in range(maxlength-1):
    MyFile.write(str(i)+",")
MyFile.close()