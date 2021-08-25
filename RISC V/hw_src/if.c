
int main(void)
{
	int score=87;
	int grade;

	if(score >= 80)
		grade = 1;

	else if(score < 80 && score >= 60)
		grade = 2;

	else if(score < 60 && score >= 40)
		grade = 3;

	else if(score < 40 && score >= 20)
		grade = 4;

	else
		grade = 5;

	return 0;

}
