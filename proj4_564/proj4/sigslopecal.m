function [offsetvalue]= sigslopecal(u)
global offsetval 
sum=0;
dimen=size(u) ;
dimen(1);
for i = 1:dimen(1)
    sum=sum+u(i);
end
offsetval=1.05*sum/dimen(1) ;



offsetvalue=offsetval;
end
