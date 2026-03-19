all : 
	main.c order_generator.c processor.c inventory.c logger.c -o warehouse

run : 
	./warehouse
	
clean : 
	rm -f warehouse orders.log
