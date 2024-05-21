DROP DATABASE IF EXISTS busstop;
CREATE DATABASE IF NOT EXISTS busstop;
USE busstop;

CREATE TABLE IF NOT EXISTS Way (
	num_way SMALLINT PRIMARY KEY,
    
	title_way VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS Station (
	num_st SMALLINT PRIMARY KEY,
    
	title_st VARCHAR(50) NOT NULL,
	distance SMALLINT NOT NULL
);

CREATE TABLE IF NOT EXISTS Station_Way (
	num_way SMALLINT,
	num_st SMALLINT,
	PRIMARY KEY (num_way, num_st),
    
    FOREIGN KEY (num_way) REFERENCES Way (num_way),
    FOREIGN KEY (num_st) REFERENCES Station (num_st)
);

CREATE TABLE IF NOT EXISTS Bus (
	num_bus SMALLINT PRIMARY KEY,
    
	model VARCHAR(30) NOT NULL,
	count_places TINYINT NOT NULL
);

CREATE TABLE IF NOT EXISTS Rays (
	num_way SMALLINT,
	time_hour TINYINT,
	time_min TINYINT,
	PRIMARY KEY (num_way, time_hour, time_min),
    
	num_bus SMALLINT NOT NULL,
    
    FOREIGN KEY (num_way) REFERENCES Way (num_way),
    FOREIGN KEY (num_bus) REFERENCES Bus (num_bus)
);

CREATE TABLE IF NOT EXISTS Ticket (
	place TINYINT,
	num_way SMALLINT,
	time_hour TINYINT,
	time_min TINYINT,
	PRIMARY KEY (place, num_way, time_hour, time_min),
    
	num_st SMALLINT,
    
    FOREIGN KEY (num_way, time_hour, time_min) REFERENCES Rays (num_way, time_hour, time_min)
);