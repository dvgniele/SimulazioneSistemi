# Perrella Daniele - Simulazione di Sistemi 2021-2022

---

> Repository per il progetto del corso di Simulazione di Sistemi


## Table of Contents


<!--ts-->
* [Features](#features)
* [Wiki](#wiki)
<!--te-->
###


---

<a name="features"></a>
Features 
========


- [x] Feature Done 
- [ ] Feature Not done yet


---

<a name="wiki"></a>
Wiki
====

È stata modificata la classe queueinglib::Queue, introducendo i metodi ```getCapacity``` e ```setCapacity``` come segue:

> in Queue.h
```
public:     
    void setCapacity(int _capacity);
    int getCapacity();
    ...
```

> in Queue.cc
```
void Queue::setCapacity(int capacity)
{
    this->capacity = capacity;
}

int Queue::getCapacity()
{
    return capacity;
}
```

Ed eliminando i gates di default, data la generazione dinamica nuovi gate. La modifica risulta come segue:

> in Queue.ned (prima)
```
gates:
    input in[];
    output out;
```
> in Queue.ned (dopo)
```
gates:
    //input in[];
    //output out;
```

È stato inoltre modificato il metodo ```endService``` in modo tale da aggiungere dati riguardanti la coda, all'uscita del job

> in Queue.cc
```
void Queue::endService(Job *job)
{
    ...

    auto par_jobs = "n_jobs";
    auto mpar = job->par(par_jobs);
    mpar.setDoubleValue(queue.length());
    
    auto par_idle = "is_sv_idle";
    mpar = job->par(par_idle);
    mpar.setBoolValue(queue.isEmpty());

    send(job, "out");
}

```
