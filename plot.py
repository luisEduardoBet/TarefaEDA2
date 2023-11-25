
import matplotlib.pyplot as plt 
  
x1 = [1,2,5,10,20,50,100,200,500,1000,2000,5000,10000] 
y2 = [1,2,4,8,16,32,64,128,256,512,1024,2056,5112]
   
plt.plot(x1, y2) 
plt.legend(["AVL"],loc = "lower right")
  
plt.xlabel("Tamanho do Conjunto") 
plt.ylabel("Esforço") 
plt.title('Árvores - Inserção') 
plt.show() 
