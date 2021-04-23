from django.shortcuts import render
from django.http import HttpResponse

# Create your views here.
def home_page(request):
	return render(request,'home.html',{
		'new_item_text':request.POST.get('item_text',''),
	})
	#pass
