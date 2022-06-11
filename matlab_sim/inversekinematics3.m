function [a1,a2,a3] = inversekinematics (x,y)
l1=10;
l2=10;
l3=10;
a=90;
x2=x-l3*cos(a);
y2=y-l3*sin(a);
a2=acos((x2^2+y2^2-l1^2-l2^2)/(2*l1*l2));
a1=acos((((l1+l2*cos(a2))*x2)+(l2*sin(a2)*y2))/(x2^2+y^2))
a3=a-a2-a1;
end
