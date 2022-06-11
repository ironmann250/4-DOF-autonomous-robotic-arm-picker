a1=deg2rad(-120);
a2=deg2rad(45);
a3=deg2rad(90);
figure;
while(1)
[x1,x2,x3,x4,y1,y2,y3,y4]=forwardkinematics3(a1,a2,a3);
disp([x3,y3,rad2deg(a2)]);
plot([x1,x2,x3] ,[y1,y2,y3],'o','MarkerFaceColor','g','MarkerSize',8);
line([x1,x2],[y1,y2],'color','r');
line([x2,x3],[y2,y3],'color','b');
line([x3,x4],[y3,y4],'color','g');
axis([-20 20 -20 20]);
[x,y]=ginput(1);
[a1,a2,a3]=inversekinematics3(x,y);
disp('      x          y      deg');
disp([x,y,rad2deg(atan2(y,x))]);
end



