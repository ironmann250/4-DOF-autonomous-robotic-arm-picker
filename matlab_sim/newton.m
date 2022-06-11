%two params newton min func
syms x1 x2 a b;
fun='x1^2+25*x2^2'; %test func
ezplot(fun);
%fun='10*cos(x1)+10*cos(x1+x2)';
e=0.01;
xk=[7;7];%xk begines at x0
k=0; %iterations counter
while(1)  
d1=diff(fun,x1);
d2=diff(fun,x2);
gradient=[double(subs([d1],xk(1)));double(subs([d2],xk(2)))];
d1d1=diff(d1,x1);
d1d2=diff(d1,x2);
d2d1=diff(d2,x1);
d2d2=diff(d2,x2);
hessian=[double(subs([d1d1],xk(1))),double(subs([d1d2],xk(2)));double(subs([d2d1],xk(1))),double(subs([d2d2],xk(2)))];
invhessian=inv(hessian);
xk=xk-(invhessian*gradient);
if (sqrt(sum(gradient.^2))<= e)
   break;
end
k=k+1;
end
clc;
disp('iterations');
disp(k);
disp('gradient=');
disp(gradient);
disp('hessian=');
disp(hessian);
disp('xk');
disp(xk);