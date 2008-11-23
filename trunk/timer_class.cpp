struct timer_class {
	std::vector<int> timers;
	timer_class () {
		
	}
	timer_class(int num_timers) {
		for (int i = 0; i < num_timers; ++i)
			timers.push_back(0);
	}
	void update_timers() {
		for (int i = 0; i < (int)timers.size(); ++i)
			if(timers[i]>0) timers[i]--;
	}
	bool zero(int index, int ticks) {
		if (index >= (int)timers.size()) return false;
		if (timers[index] == 0) {
			timers[index] = ticks;
			return true;
		}
		return false;
	}
};
