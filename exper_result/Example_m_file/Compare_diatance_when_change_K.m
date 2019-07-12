clear
pkg load io
x1=xlsread('/home/kanin/ROSbag/4_robot_planar_move_Kvl=1000Cvl=0/_slash_amr_0_slash_pose2d.csv','B2:B1100');
x2=xlsread('/home/kanin/ROSbag/4_robot_planar_move_Kvl=1000Cvl=20/_slash_amr_0_slash_pose2d.csv','B2:B1100');
x3=xlsread('/home/kanin/ROSbag/4_robot_planar_move_Kvl=1000Cvl=50/_slash_amr_0_slash_pose2d.csv','B2:B1100');
x4=xlsread('/home/kanin/ROSbag/4_robot_planar_move_Kvl=2000Cvl=0/_slash_amr_0_slash_pose2d.csv','B2:B1100');

%x1=x1(:,1);
period=100;  % in Hz
data_size=size(x3);
data_size=data_size(1,1);
end_t=(1/period)*(data_size-1);
time=0:1/period:end_t;
time=time';

plot(time,x1,'b')
hold on
plot(time,x2,'r')
hold on
plot(time,x3,'g')
hold on
plot(time,x4,'m')
hold on
grid on

title('Compare robot distance when change K')
xlabel('Time(s)') 
ylabel('Velocity (m/s)') 
set(gca, "linewidth", 2, "fontsize", 15)
h = legend ("K300", "K500", "K1000","K2000");
legend (h, "location", "northeastoutside");
set (h, "fontsize", 20);