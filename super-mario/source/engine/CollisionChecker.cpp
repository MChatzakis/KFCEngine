#include "./CollisionChecker.h"

CollisionChecker CollisionChecker::singleton;

auto CollisionChecker::GetSingleton(void) -> CollisionChecker&
{
	return singleton;
}
auto CollisionChecker::GetSingletonConst(void) -> const CollisionChecker&
{
	return singleton;
}

void CollisionChecker::Register(Sprite* s1, Sprite* s2, const Action& f)
{
	assert(!In(s1, s2));
	entries.push_back(std::make_tuple(s1, s2, f));
}

auto CollisionChecker::Find(Sprite* s1, Sprite* s2) -> std::list<Entry>::iterator
{
	return std::find_if(
		entries.begin(),
		entries.end(),
		[s1, s2](const Entry& e)
		{
			return (std::get<0>(e) == s1 && std::get<1>(e) == s2) || (std::get<0>(e) == s2 && std::get<1>(e) == s1);
		});
}

void CollisionChecker::Cancel(Sprite* s1, Sprite* s2)
{
	entries.erase(Find(s1, s2));
}

void CollisionChecker::Check(void) const
{
	for (auto& e : entries)
		if (std::get<0>(e)->CollisionCheck(std::get<1>(e))) {
			std::get<2>(e)(std::get<0>(e), std::get<1>(e));
		}
}

bool CollisionChecker::In(Sprite* s1, Sprite* s2) {
	std::list<Entry>::iterator it = Find(s1, s2);
	if (it != entries.end()) {
		return true;
	}
	return false;
}

void CollisionChecker::cancelAllTuplesOf(Sprite* s) {

	for (size_t size = 0; size < entries.size(); ++size) {
		auto e = std::find_if(
			entries.begin(),
			entries.end(),
			[s](const Entry& e)
			{
				return (std::get<0>(e) == s || std::get<1>(e) == s);
			});

		if (e == entries.end()) {
			break; //found all
		}
		entries.erase(e);
	}
}