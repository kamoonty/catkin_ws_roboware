clear
pkg load io
v1=xlsread('/home/kanin/ROSbag/4_robot_planar_move_Kvl=1000Cvl=0/_slash_amr_0_slash_cmd_vel.csv','C2:C1150');
v2=xlsread('/home/kanin/ROSbag/4_robot_planar_move_Kvl=1000Cvl=10/_slash_amr_0_slash_cmd_vel.csv','C2:C1150');
v3=xlsread('/home/kanin/ROSbag/4_robot_planar_move_Kvl=1000Cvl=20/_slash_amr_0_slash_cmd_vel.csv','C2:C1150');
%v4=xlsread('/home/kanin/ROSbag/4_robot_planar_move_Kvl=1000Cvl=50/_slash_amr_0_slash_cmd_vel.csv','C2:C1150');

%x1=x1(:,1);
period=100;  % in Hz
data_size=size(v3);
data_size=data_size(1,1);
end_t=(1/period)*(data_size-1);
time=0:1/period:end_t;
time=time';

plot(time,v1,'b')
hold on
plot(time,v2,'r')
hold on
plot(time,v3,'g')
hold on
%plot(time,v4,'m')
hold on
grid on

title('Compare robot velocity when change K')
xlabel('Time(s)') 
ylabel('Velocity (m/s)') 
set(gca, "linewidth", 2, "fontsize", 15)
h = legend ("c0", "c10", "c20","c50");
legend (h, "location", "northeastoutside");
set (h, "fontsize", 20);