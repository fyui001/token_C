SET character_set_database = utf8;
TRUNCATE token;
LOAD DATA LOCAL INFILE 'token.csv' INTO TABLE `token` FIELDS TERMINATED BY ',' (`token`);
