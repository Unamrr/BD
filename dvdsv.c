Dianochka=# \d employees
                                  Table "public.employees"
 Column  |       Type        | Collation | Nullable |                Default

---------+-------------------+-----------+----------+---------------------------
------------
 id      | integer           |           | not null | nextval('employees_id_seq'
::regclass)
 name    | character varying |           |          |
 manager | integer           |           |          |
Indexes:
    "employees_pkey" PRIMARY KEY, btree (id)
Foreign-key constraints:
    "employees_manager_fkey" FOREIGN KEY (manager) REFERENCES employees(id)
Referenced by:
    TABLE "employees" CONSTRAINT "employees_manager_fkey" FOREIGN KEY (manager)
REFERENCES employees(id)
Triggers:
    trg_employees_time_check BEFORE INSERT OR DELETE OR UPDATE ON employees FOR
EACH ROW EXECUTE FUNCTION trg_employees_time_check_func()

