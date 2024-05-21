set transaction isolation level read committed; 
start transaction; 

select * from ticket for share nowait; 
lock table ticket write; 

select * from ticket where 
num_way = 1 and num_st is NULL; 

update ticket set num_st = 20 where 
place = 3 and num_way = 1 and time_hour = 9 
and time_min = 0; 

unlock tables;
commit;