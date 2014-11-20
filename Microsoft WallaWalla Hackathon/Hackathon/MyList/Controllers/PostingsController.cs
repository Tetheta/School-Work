using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using System.Web.Http.Description;
using MyList.Models;

namespace MyList.Controllers
{
    public class PostingsController : ApiController
    {
        private MyListDBEntities db = new MyListDBEntities();

        // GET api/Postings
        public IQueryable<Posting> GetPostings()
        {
            return db.Postings;
        }

        // GET api/Postings/5
        [ResponseType(typeof(Posting))]
        public IHttpActionResult GetPosting(int id)
        {
            Posting posting = db.Postings.Find(id);
            if (posting == null)
            {
                return NotFound();
            }

            return Ok(posting);
        }

        // PUT api/Postings/5
        public IHttpActionResult PutPosting(int id, Posting posting)
        {
            //copy all existing images into new post
            Posting oldPosting = db.Postings.Find(id);
            if (oldPosting != null) { 
                if (posting.image1 == null)
                    posting.image1 = oldPosting.image1;
                if (posting.image2 == null)
                  posting.image2 = oldPosting.image2;
                if (posting.image3 == null)
                    posting.image3 = oldPosting.image3;
                if (posting.image4 == null)
                    posting.image4 = oldPosting.image4;
                if (posting.images == null || posting.images == 0)
                    posting.images = oldPosting.images;
            }

            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }
            if (id != posting.Id)
            {
                return BadRequest();
            }

            db.Entry(oldPosting).CurrentValues.SetValues(posting);

            //db.Entry(posting).State = EntityState.Modified;

            try
            {
                db.SaveChanges();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!PostingExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return StatusCode(HttpStatusCode.NoContent);
        }

        // POST api/Postings
        [ResponseType(typeof(Posting))]
        public IHttpActionResult PostPosting(Posting posting)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            db.Postings.Add(posting);

            try
            {
                db.SaveChanges();
            }
            catch (DbUpdateException)
            {
                if (PostingExists(posting.Id))
                {
                    return Conflict();
                }
                else
                {
                    throw;
                }
            }

            return CreatedAtRoute("DefaultApi", new { id = posting.Id }, posting);
        }

        // DELETE api/Postings/5
        [ResponseType(typeof(Posting))]
        public IHttpActionResult DeletePosting(int id)
        {
            Posting posting = db.Postings.Find(id);
            if (posting == null)
            {
                return NotFound();
            }

            db.Postings.Remove(posting);
            db.SaveChanges();

            return Ok(posting);
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }

        private bool PostingExists(int id)
        {
            return db.Postings.Count(e => e.Id == id) > 0;
        }
    }
}