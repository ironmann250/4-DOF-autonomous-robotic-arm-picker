function [a1,a2,a3] = inversekinematics (x,y)
l1=10;
l2=10;
a2=acos((x^2+y^2-l1^2-l2^2)/(2*l1*l2));
a1=atan2(y,x)-atan2((l2*sin(a2)),(l1+l2*cos(a2)));
a3=0;
end
