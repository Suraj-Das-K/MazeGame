I = imread('C:\Users\surajdas k\Desktop\images\iiscblueprintgs.png');
J=imbinarize(I);

fid=fopen('C:\Users\surajdas k\Desktop\images\iischex.txt','w');

 fprintf(fid,'{');
for i=1:1:240
    fprintf(fid,'{');
      for j=1:1:40
        
        l=[J(i,8*(j-1)+1) J(i,8*(j-1)+2) J(i,8*(j-1)+3) J(i,8*(j-1)+4) J(i,8*(j-1)+5) J(i,8*(j-1)+6) J(i,8*(j-1)+7) J(i,8*(j-1)+8)];
        m=binaryVectorToHex(l);
        fprintf(fid,'0x');
        fprintf(fid,'%s',m);
        
        if(j~=40)
            fprintf(fid,',');
        end
      end
    fprintf(fid,'}');
    if(i~=240)
            fprintf(fid,',');
    end
        fprintf(fid,'\n');
 end
    fprintf(fid,'}');
    fclose(fid);