data Sprm_rp_carry_info;
    set mr_mst.Sprm_rp_carry_info;

    call symput("orabm", compress("'"|STDDT|"'"));
run;

data pos_info;
    set marora9.sprm_pst;

    where stddt = &orabm.;

proc sql;
    create table Sprm_rp_carry_info2 as
    select a.*
         , b.PRDT_ID
    from Sprm_rp_carry_info a
    left outer join pos_info b
      on a.prtflid = b.prtflid
     and a.stditemcd = b.stditemcd;
quit;