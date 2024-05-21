set transaction isolation level read committed; 
start transaction; 

select * from ticket for update; 
select * from bus for update; 
select * from rays for update;  

set @curr_bus = (select num_bus from rays where 
num_way = 1 and time_hour = 9 and time_min = 0);

set @new_bus = (select num_bus from bus where 
num_bus != @curr_bus and count_places >=(
select count(*) from ticket where num_way = 1 
and time_hour = 9 and time_min = 0 and num_st is not null) 
limit 1);

select @curr_bus, @new_bus;

update rays set num_bus = @new_bus where 
num_way = 1 and time_hour = 9 and time_min = 0;

unlock tables;
commit;


