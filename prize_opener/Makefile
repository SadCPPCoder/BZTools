CONFIG=-std=c++11 -lpthread -g

prize_opener_main: prize_opener_ui
	g++ -o prize_opener_main main.cpp PrizeOpenerUI.o PrizeOpener.o PrizeOpenerConfig.o PrizeInfo.o CandidateInfo.o PrizeOwnerInfo.o ${CONFIG}
prize_opener_ui: prize_opener
	g++ -c PrizeOpenerUI.cpp ${CONFIG}
prize_opener: prize_info candidate_info prize_owner_info prize_opener_config
	g++ -c PrizeOpener.cpp ${CONFIG}
prize_opener_config:
	g++ -c PrizeOpenerConfig.cpp ${CONFIG}
prize_owner_info: prize_info candidate_info
	g++ -c PrizeOwnerInfo.cpp  ${CONFIG}
prize_info:
	g++ -c PrizeInfo.cpp  ${CONFIG}
candidate_info:
	g++ -c CandidateInfo.cpp  ${CONFIG}

clean:
	rm *.o
	rm prize_opener_main
