# שם קובץ ההרצה הסופי
TARGET = ch

# קבצי המקור
SRCS = ch.cpp

# קבצי אובייקט
OBJS = $(SRCS:.cpp=.o)

# קומפיילר ודגלים
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pg     # -pg מאפשר תמיכה ב־gprof
LDFLAGS = -pg

# כלל ברירת המחדל
all: $(TARGET)

# איך לקמפל את קובץ ההרצה
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# איך לקמפל קובץ cpp לקובץ o
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ניקוי קבצים זמניים
clean:
	rm -f $(OBJS) $(TARGET) gmon.out profile.txt

# הרצה + הפקת פרופיל gprof
profile: $(TARGET)
	./$(TARGET)
	gprof $(TARGET) gmon.out > profile.txt
	cat profile.txt
