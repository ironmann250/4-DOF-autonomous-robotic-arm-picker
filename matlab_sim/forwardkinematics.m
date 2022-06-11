function [x1,x2,x3,y1,y2,y3] = forwardkinematics (a1,a2,a3)
   l1=10;
   l2=10;
   x1=0;
   y1=0;
   x2=l1*cos(a1);
   y2=l1*sin(a1);
   x3=x2+l2*cos(a1+a2);
   y3=y2+l2*sin(a1+a2);
end