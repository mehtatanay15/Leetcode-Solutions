# Write your MySQL query statement below
select * ,
    CASE 
        when x+y>z and y+z>x and x+z>y 
        then 'Yes'
        else 'No'
        END AS triangle
FROM Triangle;
