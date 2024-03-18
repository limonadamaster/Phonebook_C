IF EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[PHONE_NUMBERS]') AND type in (N'U'))
	DROP TABLE [PHONE_NUMBERS]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[PERSONS]') AND type in (N'U'))
	DROP TABLE [PERSONS]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[PHONE_TYPES]') AND type in (N'U'))
	DROP TABLE [PHONE_TYPES]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[CITIES]') AND type in (N'U'))
	DROP TABLE [CITIES]
GO	

DROP PROCEDURE   SP_DESCRIPTION_FOR_COLUMN
go
CREATE PROCEDURE SP_DESCRIPTION_FOR_COLUMN
(
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128),
    @propertyValue NVARCHAR(MAX)
)
AS
BEGIN
    DECLARE @name NVARCHAR(128) = 'Description',
            @level0type NVARCHAR(60) = N'Schema',
            @level0name NVARCHAR(128) = N'dbo',
            @level1type NVARCHAR(60) = N'Table',
            @level1name NVARCHAR(128) = @tableName,
            @level2type NVARCHAR(60) = N'Column',
            @level2name NVARCHAR(128) = @columnName;

    DECLARE @sql NVARCHAR(MAX);

    SET @sql = N'EXEC sp_addextendedproperty '
        + N'@name = ''' + @name + ''', '
        + N'@value = ''' + @propertyValue + ''', '
        + N'@level0type = ''' + @level0type + ''', '
        + N'@level0name = ''' + @level0name + ''', '
        + N'@level1type = ''' + @level1type + ''', '
        + N'@level1name = ''' + @level1name + ''', '
        + N'@level2type = ''' + @level2type + ''', '
        + N'@level2name = ''' + @level2name + ''';';

    EXEC sp_executesql @sql;
END;
GO
DROP PROCEDURE   SP_TABLE_DESCRIPTION
go

CREATE PROCEDURE SP_TABLE_DESCRIPTION
(
    @tableName NVARCHAR(128),
    @propertyValue NVARCHAR(MAX)
)
AS
BEGIN
    DECLARE @name NVARCHAR(128) = @tableName,
            @level0type NVARCHAR(60) = N'Schema',
            @level0name NVARCHAR(128) = N'dbo',
            @level1type NVARCHAR(60) = N'Table',
            @level1name NVARCHAR(128) = @tableName,
            @level2type NVARCHAR(60) = NULL, 
            @level2name NVARCHAR(128) = NULL; 

    DECLARE @TABLE NVARCHAR(MAX);

    SET @TABLE = N'EXEC sp_addextendedproperty '
        + N'@name = ''' + @name + ''', '
        + N'@value = ''' + @propertyValue + ''', ' -- Corrected parameter name
        + N'@level0type = ''' + @level0type + ''', '
        + N'@level0name = ''' + @level0name + ''', '
        + N'@level1type = ''' + @level1type + ''', '
        + N'@level1name = ''' + @level1name + ''', '
        + N'@level2type = NULL, ' -- Specify NULL for table-level property
        + N'@level2name = NULL;'; -- Specify NULL for table-level property

    EXEC sp_executesql @TABLE;
END;
GO
--TABLES 
CREATE TABLE [CITIES]
	(
	[ID] [INT] IDENTITY(1,1) NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[NAME] NCHAR(16) NOT NULL,
	[AREA] NCHAR(16) NOT NULL,
	)
ALTER TABLE  CITIES
ADD CONSTRAINT PK_CITIES_ID PRIMARY KEY(ID)

EXEC dbo.SP_DESCRIPTION_FOR_COLUMN 'CITIES', 'ID', 'Identificator for City';
EXEC dbo.SP_DESCRIPTION_FOR_COLUMN 'CITIES', 'NAME', 'Name of City';
EXEC dbo.SP_DESCRIPTION_FOR_COLUMN 'CITIES', 'AREA', 'City in Area';
EXEC dbo.SP_DESCRIPTION_FOR_COLUMN 'CITIES', 'UPDATE_COUNTER', 'Update counter of city';
EXEC SP_TABLE_DESCRIPTION'CITIES', 'Table for every City';
GO

CREATE INDEX IX_CITIES
ON [CITIES] (NAME)

GO
	
CREATE TABLE [PHONE_TYPES]
	(
	[ID] [INT] IDENTITY(1,1) NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[PHONE_TYPE] NCHAR(16) NOT NULL,
	)
	
ALTER TABLE [PHONE_TYPES]
ADD CONSTRAINT PK_PHONE_TYPES_ID PRIMARY KEY(ID)
EXEC dbo.SP_DESCRIPTION_FOR_COLUMN 'PHONE_TYPES', 'PHONE_TYPE', 'Type of phone on subscriber';
	EXEC SP_TABLE_DESCRIPTION'PHONE_TYPES', 'Table for every subscriber phone';
CREATE TABLE [PERSONS]
	(
	[ID] [INT] IDENTITY(1,1) NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[FIRST_NAME] NCHAR(64) NOT NULL,
	[SECOND_NAME] NCHAR(64) NOT NULL,
	[THIRD_NAME] NCHAR(64) NOT NULL,
	[UCN] NCHAR (32) NOT NULL,
	[CITY_ID] [INT] NOT NULL,
	[ADDRESS] NCHAR (64) NOT NULL,
	)
ALTER TABLE [PERSONS]
ADD CONSTRAINT FK_PERSONS_TOWN_ID FOREIGN KEY ([CITY_ID]) REFERENCES CITIES(ID)

ALTER TABLE [PERSONS]
ADD CONSTRAINT PK_PERSONS_ID PRIMARY KEY(ID)

CREATE INDEX IX_PERSONS
ON [PERSONS] (UCN)
GO

EXEC dbo.SP_DESCRIPTION_FOR_COLUMN 'PERSONS', 'ID', 'Identificator for Person';
EXEC dbo.SP_DESCRIPTION_FOR_COLUMN 'PERSONS', 'UCN', 'Identificator for Person in Bulgaria';
EXEC dbo.SP_DESCRIPTION_FOR_COLUMN 'PERSONS', 'CITY_ID', 'Foreign key to city';
EXEC dbo.SP_TABLE_DESCRIPTION'PERSONS', 'Table for every Person';

CREATE TABLE [PHONE_NUMBERS]
	(
	[ID] [INT] IDENTITY(1,1)  NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[PERSON_ID] [INT] NOT NULL,
	[PHONE_TYPE_ID] [INT] NOT NULL,
	[PHONE] NCHAR(32) NOT NULL,
	)

ALTER TABLE [PHONE_NUMBERS]
ADD CONSTRAINT PK_PHONE_NUMBERS_ID PRIMARY KEY(ID)

ALTER TABLE [PHONE_NUMBERS]
ADD CONSTRAINT FK_PHONE_NUMBERS_PERSON_ID FOREIGN KEY (PERSON_ID) REFERENCES PERSONS(ID)
	
ALTER TABLE [PHONE_NUMBERS]
ADD	CONSTRAINT FK_PHONE_NUMBERS_PHONE_TYPE_ID FOREIGN KEY (PHONE_TYPE_ID) REFERENCES PHONE_TYPES(ID)
GO

CREATE INDEX IX_PHONE_NUMBERS_ID	
ON [PHONE_NUMBERS] (ID)
EXEC dbo.SP_DESCRIPTION_FOR_COLUMN 'PHONE_NUMBERS', 'Phone', 'Phone number';
GO






GO




select * from sys.extended_properties



SELECT * FROM CITIES



