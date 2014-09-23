#include "JobManager.hpp"

#include "Memory Manager/MemoryManager.hpp"

JobManager::JobManager(int numWorkers /*= 0*/)
{
	for (int workerIndex = 0; workerIndex < numWorkers; workerIndex++)
	{
		m_workers.push_back(new ThreadedWorker(workerIndex));
	}
}

void JobManager::update()
{
	if (m_workers.size() == 0)
	{
		//TODO do a job
	}
	else
	{
		for (unsigned int workerIndex = 0; workerIndex < m_workers.size(); workerIndex++)
		{
			//check to see if they have a completed job
			if (m_workers[workerIndex]->m_state == WORKER_DONE)
			{
				m_completedJobs.push_back(m_workers[workerIndex]->m_job);
				m_workers[workerIndex]->m_job = nullptr;
				m_workers[workerIndex]->m_state = WORKER_IDLE;
			}
			//if they have no jobs, and a job is available, give them one
			if (m_workers[workerIndex]->m_state == WORKER_IDLE && !m_unclaimedJobs.empty())
			{
				m_workers[workerIndex]->m_job = m_unclaimedJobs.top();
				m_workers[workerIndex]->m_state = WORKER_WORKING;
				m_unclaimedJobs.pop();
			}
		}
	}

	while (!m_completedJobs.empty())
	{
		m_completedJobs.back()->callback();
		m_completedJobs.pop_back();
	}
}