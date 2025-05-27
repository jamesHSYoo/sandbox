create table STOCK_PRICES(
	BASE_DT CHAR(8)   not null,
	DATA_ID VARCHAR(100)  not null,
	CLOSE_PRIC real not null,
	BASE_PRIC real,
	REG_TIME TIMESTAMP,
	primary KEY(BASE_DT, DATA_ID)
);