str name = ""

struct stats
{
	int health = 100
	int armor = 100
	int mana = 100
}

struct inventory
{
	int sword = 100
}

start: 1

1
{
	tell: "Welcome to Dungeons and Dragons!"
	menu
	{
		"Continue...":2,
		"Exit...":end
	}
}

2
{
	tell: "What's your name?"
	get: "?? ", 
	if(name == "")
	{
		tell: "Please enter a name!"
		goto: 2
	}
	goto: 3
}

3
{
	tell: "Hi! $[name], nice to meet you!!"
	menu
	{
		"What's your name??":4,
		"Say nothing...":5
	}
}

end
{
	tell: "thanks for playing"
	exit
}
