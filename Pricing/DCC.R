library(lubridate)

DayCountConvention <- function(nType,StaD,EndD)
{
  if (nType %in% c(1,7,8,9,10))
  {
    SL <- leap_year(StaD)
    EL <- leap_year(EndD)
    LFlag <- SL+EL*2
  }
  
  ND <- length(StaD)
  YF <- rep(0,ND)
  
  for (i in 1:ND)
  {
    D1 <- StaD[i]
    D2 <- EndD[i]
    
    if (nType == 1)        # Act/Act ISDA
    {
      if (LFlag[i] == 0)
      {
        YF[i] <- as.numeric(D2-D1)/365
      } else if (LFlag[i] == 1)
      {
        YEnD <- as.Date(paste(year(D1),12,31, sep='-'))
        YStD <- as.Date(paste(year(D2),1,1, sep='-'))
        YF[i] <- as.numeric(D2-YStD)/365+as.numeric(YEnD-D1+1)/366
      } else if (LFlag[i] == 2)
      {
        YEnD <- as.Date(paste(year(D1),12,31, sep='-'))
        YStD <- as.Date(paste(year(D2),1,1, sep='-'))
        YF[i] <- as.numeric(D2-YStD)/366+as.numeric(YEnD-D1+1)/365
      } else
      {
        YF[i] <- as.numeric(D2-D1)/366
      }
      
    } else if (nType == 2)    # Act/360
    {
      YF[i] <- (D2-D1)/360
      
    } else if (nType == 3)    # Act/365
    {
      YF[i] <- (D2-D1)/365
      
    } else if (nType == 4)    # 30/Act  ---> 30/365
    {
      D1 <- D1-(day(D1) == 31)
      D2 <- D2-((day(D1) == 30 | day(D1) == 31) & day(D2) == 31)
      YF[i] <- DCF30(year(D1),month(D1),day(D1),year(D2),month(D2),day(D2),365)
      
    } else if (nType == 5)    # 30/360
    {
      D1 <- D1-(day(D1) == 31)
      D2 <- D2-((day(D1) == 30 | day(D1) == 31) & day(D2) == 31)
      YF[i] <- DCF30(year(D1),month(D1),day(D1),year(D2),month(D2),day(D2),360)
      
    } else if (nType == 6)    # 30/365  ---> 30/360 변형
    {
      D1 <- D1-(day(D1) == 31)
      D2 <- D2-((day(D1) == 30 | day(D1) == 31) & day(D2) == 31)
      YF[i] <- DCF30(year(D1),month(D1),day(D1),year(D2),month(D2),day(D2),365)
      
    } else if (nType == 7)    # NL/Act  ---> NL/365
    {
      if (LFlag[i] == 0)
      {
        SHIFT <- 0
      } else if (LFlag[i] == 1)
      {
        SHIFT <- (D1 <= as.Date(paste(year(D1),2,29, sep='-')))
      } else if (LFlag[i] == 2)
      {
        SHIFT <- (D2 >= as.Date(paste(year(D2),2, 29, sep='-')))
      } else
      {
        SHIFT <- (D1 <= as.Date(paste(year(D1),2, 29, sep='-'))) & D2 >= as.Date(paste(year(D2), 2, 29, sep='-'))
      }

      YF[i] <- as.numeric(D2-D1-SHIFT)/365

      
    } else if (nType == 8)    # NL/360
    {
      if (LFlag[i] == 0)
      {
        SHIFT <- 0
      } else if (LFlag[i] == 1)
      {
        SHIFT <- (D1 <= as.Date(paste(year(D1),2,29, sep='-')))
      } else if (LFlag[i] == 2)
      {
        SHIFT <- (D2 >= as.Date(paste(year(D2),2, 29, sep='-')))
      } else
      {
        SHIFT <- (D1 <= as.Date(paste(year(D1),2, 29, sep='-'))) & D2 >= as.Date(paste(year(D2), 2, 29, sep='-'))
      }
      
      YF[i] <- DCF30(year(D1),month(D1),day(D1),year(D2),month(D2),day(D2)-SHIFT,360)
      
    } else if (nType == 9)    # NL/365
    {
      if (LFlag[i] == 0)
      {
        SHIFT <- 0
      } else if (LFlag[i] == 1)
      {
        SHIFT <- (D1 <= as.Date(paste(year(D1),2,29, sep='-')))
      } else if (LFlag[i] == 2)
      {
        SHIFT <- (D2 >= as.Date(paste(year(D2),2, 29, sep='-')))
      } else
      {
        SHIFT <- (D1 <= as.Date(paste(year(D1),2, 29, sep='-'))) & D2 >= as.Date(paste(year(D2), 2, 29, sep='-'))
      }
      
      YF[i] <- as.numeric(D2-D1-SHIFT)/365
      
    } else if (nType == 10)   # 30E/Act  ---> 30E/365
    {
      D1 <- D1-(day(D1) == 31)
      D2 <- D2-(day(D2) == 31)
      YF[i] <- DCF30(year(D1),month(D1),day(D1),year(D2),month(D2),day(D2),365)
      
    } else if (nType == 11)   # 30E/360
    {
      D1 <- D1-(day(D1) == 31)
      D2 <- D2-(day(D2) == 31)
      YF[i] <- DCF30(year(D1),month(D1),day(D1),year(D2),month(D2),day(D2),360)
      
    } else if (nType == 12)   # 30E/365  ---> 30E/360 변형
    {
      D1 <- D1-(day(D1) == 31)
      D2 <- D2-(day(D2) == 31)
      YF[i] <- DCF30(year(D1),month(D1),day(D1),year(D2),month(D2),day(D2),365)
      
    } else if (nType == 13)   # 30E/360 ISDA
    {
      D1 <- D1-(day(D1) == 31)
      D2 <- D2-(day(D2) == 31)
      SHIFT <- ((month(D1) == 2) & (day(D1) == 28 | day(D1) == 29))*(30-day(D1))
      YF <- DCF30(year(D1),month(D1),day(D1)+SHIFT,year(D2),month(D2),day(D2),360)
      
    } else if (nType == 14)   # 30/360 US, 30U/360, 30/360 SIA 
    {
      D1 <- D1-(day(D1) == 31)
      D2 <- D2-((day(D1) == 30 | day(D1) == 31) & day(D2) == 31)
      SHIFT1 <- ((month(D1) == 2) & (day(D1) == 28 | day(D1) == 29))*(30-day(D1))
      SHIFT2 <- (SHIFT1>0 & (month(D2) == 2) & (day(D2) == 28 | day(D2) == 29))*(30-day(D2))
      YF[i] <- DCF30(year(D1),month(D1),day(D1)+SHIFT1,year(D2),month(D2),day(D2)+SHIFT2,360)
    } 
  }
  return(YF)
}

DCF30 <- function(Y1,M1,D1,Y2,M2,D2,NY)
{
  DCF <- ((Y2-Y1)*360+(M2-M1)*30+D2-D1)/NY
  return(DCF)
}


StaD <- ymd(c("2019-05-27", "2019-08-27", "2019-11-27", "2020-02-27", "2020-05-27", "2020-08-27"))
EndD <- ymd(c("2019-08-27", "2019-11-27", "2020-02-27", "2020-05-27", "2020-08-27", "2020-11-27"))


DayCountConvention(1,StaD,EndD)
DayCountConvention(2,StaD,EndD)
DayCountConvention(3,StaD,EndD)
DayCountConvention(4,StaD,EndD)
DayCountConvention(5,StaD,EndD)
DayCountConvention(6,StaD,EndD)
DayCountConvention(7,StaD,EndD)
DayCountConvention(8,StaD,EndD)
DayCountConvention(9,StaD,EndD)
DayCountConvention(10,StaD,EndD)
DayCountConvention(11,StaD,EndD)
DayCountConvention(12,StaD,EndD)
DayCountConvention(13,StaD,EndD)
DayCountConvention(14,StaD,EndD)
