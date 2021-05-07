// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define LASSERT(cond, msg, ...) if(!(cond)) { UE_LOG(LogTemp, Error, TEXT(msg), __VA_ARGS__); }