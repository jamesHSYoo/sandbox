from fastapi import FastAPI

app = FastAPI()

@app.get("/")
async def root():
    return {"message": "Hello, World!"}


@app.get("/gettest")
async def root():
    return {"message" : "test sucess"}