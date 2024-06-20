"""
URL configuration for delivery project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/5.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from app01 import views

urlpatterns = [
    # path('admin/', admin.site.urls),

    # ww.com/index -> 后面的函数


    path('user/info/', views.user_info_list),
    path('user/add/', views.user_add),
    path('user/edit/<int:user_id>/', views.user_edit),
    path('user/delete/<int:user_id>/', views.user_delete),
    path('menu/info/find/', views.menu_find),
    path('menu/info/', views.menu_info),
    path('menu/add/', views.auth_add),
    path('menu/edit/<int:menu_id>/', views.menu_edit),
    path('menu/delete/<int:menu_id>/', views.menu_delete),
    # path('menu/add/', views.menu_add),
    path('menu/checkout/', views.menu_checkout),
    path('auth/', views.auth_way),
    path('auth/add/', views.auth_add),
    path('login/', views.login),
    path('', views.index),
]