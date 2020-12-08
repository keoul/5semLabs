create table PERSON (
    driver_id varchar(30) primary key,
    name varchar(50),
    Address varchar(100),
    
);
create table CAR (
    regno varchar(20) primary key,
    model varchar(30),
    Year int,
    
);
create table ACCIDENT (
    report_number int primary key,
    accd_date date,
    location varchar(50),
    
);
create table PARTICIPATED (
    driver_id varchar(30),
    regno varchar(20),
    report_number int,
    damage_amount int,
    foreign key (report_number) references ACCIDENT,
    foreign key (driver_id) references PERSON,
    foreign key (regno) references CAR,
);


-- ii

insert into PERSON values ("1","keoul","address 1");
insert into PERSON values ("2","dhruvik","address 2");
insert into PERSON values ("3","nimesh","address 3");
insert into PERSON values ("4","devesh","address 4");
insert into PERSON values ("5","ansh","address 5");

insert into CAR values ("1","i20",2019);
insert into CAR values ("2","scorpio",2010);
insert into CAR values ("3","xuv500",2009);
insert into CAR values ("4","jetta",2013);
insert into CAR values ("5","polo",2017);

insert into ACCIDENT values (1,DATE "2020-12-7","address 1");
insert into ACCIDENT values (2,DATE "2012-3-31","address 2");
insert into ACCIDENT values (3,DATE "2013-6-25","address 3");
insert into ACCIDENT values (4,DATE "2018-11-17","address 4");
insert into ACCIDENT values (5,DATE "2001-1-16","address 5");

insert into PARTICIPATED values ("3","4",1,11000);
insert into PARTICIPATED values ("5","5",4,12000);
insert into PARTICIPATED values ("2","4",2,70800);
insert into PARTICIPATED values ("2","3",3,2800);
insert into PARTICIPATED values ("2","1",5,68000);


-- iii

update PARTICIPATED 
set damage_amount = 25000
where report_number = 12;
--add regno = ? if you want a specific regno

-- iv

delete from ACCIDENT where (extract(year from accd_date)) = 2019;

-- v

alter table PERSON drop column A ;
alter table PERSON add A D;

-- vi

alter table PERSON add check (condition);

