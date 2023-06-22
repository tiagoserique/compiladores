program funcao (input, output); 
var  m: integer;      
function f(n: integer; var k: integer): integer; 
var p, q: integer;           
begin                    
   if n<2 then
      begin          
         f:=n; k:=0     
      end              
   else                
      begin            
         f:=f(n-1,p) + f(n-2,q);   
         k:=p+q+1      
      end;             
   write(n,k);        
end;                      
begin                          
   write(f(3,m),m); 
end. 



