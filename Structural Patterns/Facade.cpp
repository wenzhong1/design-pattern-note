#include <iostream>

using namespace std;

class MisDepartment
{
 public:
    void submitNetworkRequest()
    {
        _state = States::Received;
    }
    bool checkOnStatus()
    {
        _state = (States)(static_cast<int>(_state) + 1);
        if (_state == States::Complete)
          return true;
        return false;
    }
  private:
    enum class States : int 
    {
        Received = 0, DenyAllKnowledge, ReferClientToFacilities,
        FacilitiesHasNotSentPaperwork, ElectricianIsNotDone,
        ElectricianDidItWrong, DispatchTechnician, SignedOff, DoesNotWork,
        FixElectriciansWiring, Complete
    };
    enum States _state;
};

class ElectricianUnion
{
  public:
    void submitNetworkRequest()
    {
        _state = States::Received;
    }
    bool checkOnStatus()
    {
        _state = (States)(static_cast<int>(_state) + 1);
        if (_state == States::Complete)
          return true;
        return false;
    }
  private:
    enum class States : int 
    {
        Received, RejectTheForm, SizeTheJob, SmokeAndJokeBreak,
          WaitForAuthorization, DoTheWrongJob, BlameTheEngineer, WaitToPunchOut,
          DoHalfAJob, ComplainToEngineer, GetClarification, CompleteTheJob,
          TurnInThePaperwork, Complete
    };
    enum States _state;
};

class FacilitiesDepartment
{
  public:
    void submitNetworkRequest()
    {
        _state = States::Received;
    }
    bool checkOnStatus()
    {
        _state = (States)(static_cast<int>(_state) + 1);
        if (_state == States::Complete)
          return true;
        return false;
    }
  private:
    enum class States : int 
    {
        Received = 0, AssignToEngineer, EngineerResearches, RequestIsNotPossible,
          EngineerLeavesCompany, AssignToNewEngineer, NewEngineerResearches,
          ReassignEngineer, EngineerReturns, EngineerResearchesAgain,
          EngineerFillsOutPaperWork, Complete
    };
    enum States _state;
};

class FacilitiesFacade
{
public:
    FacilitiesFacade()
    {
        _count = 0;
    }
    void submitNetworkRequest()
    {
        _state = States::Received;
    }
    bool checkOnStatus()
    {
        _count++;
        /* Job request has just been received */
        if (_state == States::Received)
        {
            _state = (States)(static_cast<int>(_state) + 1);
            /* Forward the job request to the engineer */
            _engineer.submitNetworkRequest();
            cout << "submitted to Facilities - " << _count << 
              " phone calls so far" << endl;
        }
        else if (_state == States::SubmitToEngineer)
        {
            /* If engineer is complete, forward to electrician */
            if (_engineer.checkOnStatus())
            {
                _state = (States)(static_cast<int>(_state) + 1);
                _electrician.submitNetworkRequest();
                cout << "submitted to Electrician - " << _count << 
                  " phone calls so far" << endl;
            }
        }
        else if (_state == States::SubmitToElectrician)
        {
            /* If electrician is complete, forward to technician */
            if (_electrician.checkOnStatus())
            {
                _state = (States)(static_cast<int>(_state) + 1);
                _technician.submitNetworkRequest();
                cout << "submitted to MIS - " << _count << 
                  " phone calls so far" << endl;
            }
        }
        else if (_state == States::SubmitToTechnician)
        {
            /* If technician is complete, job is done */
            if (_technician.checkOnStatus())
              return true;
        }
		
        /* The job is not entirely complete */
        return false;
    }
    int getNumberOfCalls()

    {
        return _count;
    }
  private:
    enum class States : int 
    {
        Received = 0, SubmitToEngineer, SubmitToElectrician, SubmitToTechnician
    };
    enum States _state;
    int _count;
    FacilitiesDepartment _engineer;
    ElectricianUnion _electrician;
    MisDepartment _technician;
};

int main()
{
  FacilitiesFacade facilities;

  facilities.submitNetworkRequest();
  /* Keep checking until job is complete */
  while (!facilities.checkOnStatus())
    ;
  cout << "job completed after only " << facilities.getNumberOfCalls() << 
    " phone calls" << endl;
}