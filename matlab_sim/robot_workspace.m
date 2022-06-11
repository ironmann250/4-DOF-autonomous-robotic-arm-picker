l1 = 10;
l2 = 10; 
a1 = 0:0.1:pi/2;
a2 = 0:0.1:pi; 
[a1,a2] = meshgrid(a1,a2); 
X = l1 * cos(a1) + l2 * cos(a1 + a2); 
Y = l1 * sin(a1) + l2 * sin(a1 + a2); 
plot(X(:),Y(:),'r.'); 
  axis equal;
  xlabel('X3','fontsize',10)
  ylabel('Y3','fontsize',10)
  title('X3-Y3 coordinates for all a1 and a2 combinations','fontsize',10)