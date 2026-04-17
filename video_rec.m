
clear; clc; close all;

disp('Loading 3-body data...');
data = readmatrix('gravity.txt', 'NumHeaderLines', 2);

time = data(:, 1);
p1_x = data(:, 2); p1_y = data(:, 3);
p2_x = data(:, 4); p2_y = data(:, 5);
p3_x = data(:, 6); p3_y = data(:, 7);

disp('Data loaded! Setting up recording...');


fig = figure('Name', 'Tracking Camera Engine', 'Color', 'k', 'Position', [100, 100, 800, 800]); 
hold on; grid on; axis equal; 
set(gca, 'Color', 'k', 'GridColor', [0.3 0.3 0.3], 'XColor', 'w', 'YColor', 'w');

zoom_level = 300; 


myVideo = VideoWriter('NewtonCannon_Simulation.mp4', 'MPEG-4');
myVideo.FrameRate = 30; 
open(myVideo);



planet_radius = 100;
theta = linspace(0, 2*pi, 100);
planet_X_base = planet_radius * cos(theta);
planet_Y_base = planet_radius * sin(theta);
planet_fill = fill(p2_x(1) + planet_X_base, p2_y(1) + planet_Y_base, [0.8 0.3 0.2], 'EdgeColor', 'none'); 

trail1 = plot(p1_x(1), p1_y(1), 'c-', 'LineWidth', 1.5); 
sat1 = plot(p1_x(1), p1_y(1), 'co', 'MarkerFaceColor', 'w', 'MarkerSize', 6); 

trail3 = plot(p3_x(1), p3_y(1), 'm-', 'LineWidth', 1.5); 
sat3 = plot(p3_x(1), p3_y(1), 'mo', 'MarkerFaceColor', 'w', 'MarkerSize', 6); 

xlabel('X Position');
ylabel('Y Position');


for i = 1:5:length(time)
    
    xlim([p2_x(i) - zoom_level, p2_x(i) + zoom_level]);
    ylim([p2_y(i) - zoom_level, p2_y(i) + zoom_level]);
    
    
    planet_fill.XData = p2_x(i) + planet_X_base;
    planet_fill.YData = p2_y(i) + planet_Y_base;
    
    sat1.XData = p1_x(i); sat1.YData = p1_y(i);
    trail1.XData = p1_x(1:i); trail1.YData = p1_y(1:i);
    
    sat3.XData = p3_x(i); sat3.YData = p3_y(i);
    trail3.XData = p3_x(1:i); trail3.YData = p3_y(1:i);
    
    title(sprintf('Simulation Time: %.2f seconds', time(i)), 'Color', 'w');
    drawnow;
    
    
    frame = getframe(fig);
    writeVideo(myVideo, frame);
   
    
end


close(myVideo);


disp('saved as NewtonCannon_Simulation.mp4!');