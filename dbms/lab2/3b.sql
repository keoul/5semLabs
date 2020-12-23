create or replace total_accd (y in INT)
return INT
as
total INT
BEGIN;
select count(*) into total from accident where (extract(year from accd_date)) = y;
END;


-- 2

create or replace procedure total_damage (y in int,d_id varchar(10))
as
total_amt int
begin;
select sum(damage_amount) into total_amt from participated natural join accident
where driver_id = d_id and (extract(year from accd_date)) = y;
DBMS_OUTPUT.PUT_LINE('Total damages for driver with driver_id ='||driver_id||' in the year '|| y || ' are ' || total_amt )
end;
