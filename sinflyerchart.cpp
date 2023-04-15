#include"sinflyerchart.h"

sinflyerchart::sinflyerchart():index_of_head(1)
{
    connect(&tm_,SIGNAL(timeout()),this,SLOT(slotTimeout_()));
	tm_.start(updatetime);
}

sinflyerchart::sinflyerchart(charttype &ct_,int index_):ct(ct_),index_of_head(index_)
{
	updatechartstyle();
    connect(&tm_,SIGNAL(timeout()),this,SLOT(slotTimeout_()));
	tm_.start(updatetime);
}


void sinflyerchart::updatechartstyle(void)
{
   num_of_lines=ct.lines.size();
    for(int i=0;i!=ct.lines.size();++i)
	{
		this->addGraph();
        this->graph(i)->setName(ct.lines[i].first);
        this->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
		this->graph(i)->setPen(QPen(ct.lines[i].second,2, Qt::SolidLine));
	}
		this->legend->setVisible(true);                     
		this->legend->setFont(QFont("Helvetica", 9));        
		this->legend->setTextColor(Qt::white);
		this->legend->setBrush(QColor(255, 255, 255, 0));
		this->setBackground(ct.backgoundcolor);

		this->xAxis->setTickLabelColor(Qt::white);
		this->yAxis->setTickLabelColor(Qt::white);
		this->yAxis->setBasePen(QPen(Qt::white,2));
		this->xAxis->setBasePen(QPen(Qt::white,2));

		this->xAxis->setLabel(ct.xAxisLabel);
		this->yAxis->setLabel(ct.yAxisLabel);
		this->xAxis->setLabelColor(Qt::white);
		this->yAxis->setLabelColor(Qt::white);
		this->yAxis->setRange(ct.y_min, ct.y_max);
}

void sinflyerchart::setchartstyle(charttype &ct_)
{
	ct=ct_;
	updatechartstyle();
}

void sinflyerchart::setheadindex(const unsigned int& index_)
{
	index_of_head=index_;
}

void sinflyerchart::slotTimeout_()
{  
	static std::string updatestr;
	while(!updatestrs.empty())
	{ 
        updatestr=updatestrs.front();
		updatestrs.pop();
		QList<QString> lin=(QString::fromStdString(updatestr)).split("\r\n");
        
		if(lin.length()>1)
		{
			for(int i=0;i!=lin.length()-1;++i)
			{
				QList<QString> temp=lin[i].split(" ");
				float time=temp[0].toFloat()/1000;
				if(temp.length()>8)
				{
					for(int j=0;j!=num_of_lines;++j)
					{
						this->graph(j)->addData(time,temp[index_of_head+j].toFloat());
					}
				}
				this->xAxis->setRange(time + 1, 5, Qt::AlignRight);
			}
		}
	    this->replot();
	}

}
