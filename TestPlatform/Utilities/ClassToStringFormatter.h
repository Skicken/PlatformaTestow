#pragma once
class ClassToStringFormatter
{
	public:
	inline static const auto userToString = [](User& user)
	{
		return user.getName() + " " + user.getSurname();
	};
	inline static const auto userToStringWithType = [](User& user)
	{
		return user.getName() + " " + user.getSurname()+" "+ExternalData::EnumToString(user.getType());
	};
	inline static const auto homeworkCommitToString = [](HomeworkCommit& commit)
	{
		return commit.getDeliveryDate() + " : " + commit.getQuestion();
	};
	inline static const auto testCommitToString = [](TestCommit& commit)
	{
		std::string scorePercentage = std::to_string(commit.calculatePercentage());
		scorePercentage = scorePercentage.substr(0, 5);
		return std::string(commit.getTest().getTestName() + " " + scorePercentage + " %");
	};
	inline static const auto attendanceListToString = [](AttendanceList& list)
	{
		return list.getDate();
	};
	inline static const auto groupToString = [](Group& group)
	{
		return group.getName();
	};

};

